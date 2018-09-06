require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'xml'
require 'gumbo'
require "duktape"

class Reader < HiEngine::Object
  @stop = false
  @chapter_url

  def servce_url 
    unless @s_url
      url = 'http://box.dzzgg.com/box/lists.xml'
      @client = HTTPClient.new url
      @client.on_complete = Callback.new do |c|
        if c.getError.length == 0
          doc = XMLDocument.new FileData.new(c.path), 0
          ret = doc.xpath('//sever').first.getContent
          @s_url = js_engine.eval("common.decryptCode('#{ret}')")
          yield @s_url
        else
          yield nil
        end
      end
      @client.start
    else
      yield @s_url
    end
  end

  def js_engine
    unless @js
      @js = DuktapeEngine.new
      @js.eval(file('core.js').text)
      @js.eval(file('enc-base64.js').text)
      @js.eval(file('cipher-core.js').text)
      @js.eval(file('aes.js').text)
      @js.eval(file('crypto.js').text)
    end
    @js
  end

  def load_page url, idx
    page = Page.new 
    page.url = url
    @client = HTTPClient.new page.url
    @client.read_cache = true
    @client.retry_count = 3
    @client.on_complete = Callback.new do |c|
      @client = nil
      if c.getError.length == 0
        utf8d = Encoder.decode FileData.new(c.path), 'gb2312'
        doc = GBDocument.new utf8d
        enc_nodes = doc.css("#encrypt")
        if enc_nodes.size > 0
          enc = enc_nodes.first.getContent
          ret = js_engine.eval("common.decrypt('#{enc}', #{idx})")
          servce_url do |hu|
            if hu
              page.picture = hu + ret[0]
  
              next_node = doc.css(".fanye1 > li:last-child a").first
              next_url = nil
              if next_node.attr('href') != '#'
                next_url = url.gsub(/[^\/]+$/, next_node.attr('href'))
              end
  
              yield page, true, next_url
            else
              yield page, false, nil
            end
          end
        else
          img_node = doc.css('#nr234img img').first
          if img_node
            page.picture = img_node.attr('src')
  
            next_node = doc.css(".fanye1 > li:last-child a").first
            next_url = nil
            if next_node.attr('href') != '#'
              next_url = url.gsub(/[^\/]+$/, next_node.attr('href'))
            end
            yield page, true, next_url
          else
            yield page, false, nil
          end
        end
        
      else
        yield page, false, nil
      end
    end
    @client.start
  end

  def load_p url, idx
    load_page url, idx do |page, res, next_url| 
      if res
        loadedPage idx, true, page
        if next_url
          load_p next_url, idx + 1
        else
          on_page_count.inv true, idx + 1
        end
      else
        loadedPage idx, false, page
        on_page_count.inv false
      end
    end
  end

  # 开始解析一个章节，读取其中所有的页
  def process chapter
    @stop = false
    load_p chapter.url, 0
  end

  def stop
    @stop = true
    if @client
      @client.cancel
    end
  end

  def reloadPage page, idx, on_complete
    @stop = false
    page.status = 0
    load_page page.url, idx do |page, res, next_url| 
      if res
        on_complete.inv true, page
      else
        on_complete.inv false, page
      end
    end
  end
end
