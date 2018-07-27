require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'xml'
require "duktape"

class Reader < HiEngine::Object
  HOST_URL = 'http://manhua.fzdm.com/'
  @stop = false
  @chapter_url

  def load_page url
    root = url.gsub(/index_\d+.html$/, '')

    request root, 0
  end

  def request root_url, idx
    @client = HTTPClient.new root_url + "index_#{idx}.html"
    @client.read_cache = true
    @client.retry_count = 3
    @client.on_complete = Callback.new do |c|
      @client = nil
      return if @stop
      if c.getError.length == 0
        parse_page root_url, c.path,  idx do |idx, page, has_more|
          if idx != false
            loadedPage idx, true, page
            if has_more
              request root_url, idx+1
            else
              self.on_page_count.inv true, idx+1
            end
          else 
            loadedPage idx, false, Page.new
            self.on_page_count.inv false
          end
        end
      else
        p c.getError
        loadedPage idx, false, Page.new
        self.on_page_count.inv false
      end
    end
    @client.start
  end

  def parse_page root_url, path, idx
    begin
      unless @javascript
        @javascript = DuktapeEngine.new
        @javascript.eval file('base64.js').text
        @javascript.eval file('pro.js').text
      end
      doc = XMLDocument.new FileData.new(path), 1
      nodes = doc.xpath("//script[not(@src)]")
      node = nodes[nodes.size - 2]
      @javascript.eval node.getContent
      pic = @javascript.eval 'html_str'
      
      page = Page.new
      page.url = root_url + "index_#{idx}.html"
      pic[/src=["']([^'"]+)/]
      page.picture = $1
      
      links = doc.xpath('//*[@class="navigation"]/a')
      yield idx, page, links.last.getContent == '下一页'
    rescue Exception => e
      p e
      yield false
    end
  end

  # 开始解析一个章节，读取其中所有的页
  def process chapter
    @chapter_url = chapter.url
    @stop = false
    page = Page.new
    page.url = chapter.url
    load_page page.url
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
    @client = HTTPClient.new page.url
    @client.read_cache = false
    @client.retry_count = 3
    @client.on_complete = Callback.new do |c|
      @client = nil
      return if @stop
      if c.getError.length == 0
        page.status = 1
        root = page.url.gsub(/index_\d+.html$/, '')
        parse_page root, c.path, idx  do |idx, page|
          if idx
            on_complete.inv true, page
          else
            on_complete.inv false, page
          end
        end
      else
        page.status = -1
        on_complete.inv false, page
      end
    end
    @client.start
  end
end
