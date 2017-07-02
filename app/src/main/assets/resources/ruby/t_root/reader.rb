require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'xml'

class Reader < HiEngine::Object
  @stop = false

  def process chapter
    @stop = false
    load_page chapter.url
  end

  def load_page url, pages = [], offset = 0
    @client = HTTPClient.new url
    @client.read_cache = true
    @client.retry_count = 3
    @client.delay = 0.5
    @client.on_complete = Callback.new do |c|
      @client = nil
      return if @stop
      if c.getError.length == 0
        doc = XMLDocument.new FileData.new(c.path), 1
        rows = doc.xpath "//div[@id='gh']/div[@class='gi']/a"
        rows.each do |row|
          page = Page.new
          page.status = 0
          page.url = row.getAttribute 'href'
          pages << page
        end
        links = doc.xpath "//div[@id='ia']/a"
        next_node = nil
        links.each do |link|
          if link.getContent['Next Page'] != nil
            next_node = link
            break
          end
        end
        process_page pages, offset do
          if next_node
            n_url = next_node.attr 'href'
            load_page n_url, pages, pages.size
          else
            self.on_page_count.inv true, pages.size
          end
        end
      else
        self.on_page_count.inv false
      end
    end
    @client.start
    @client
  end

  def process_page pages, index, &block
    page = pages[index]
    url = page.url
    request_page url do |success, pic|
      if success
        page.picture = pic
        loadedPage index, true, page
        if index < pages.size - 1
          process_page pages, index + 1, &block
        else
          yield
        end
      else
        loadedPage index, false, page
      end
    end
  end

  def request_page url, read_cache = true
    @client = HTTPClient.new url
    @client.delay = 0.5
    @client.read_cache = read_cache
    @client.retry_count = 3
    @client.on_complete = Callback.new do |c|
      @client = nil
      if c.getError.length == 0
        doc = XMLDocument.new FileData.new(c.path), 1
        img_node = doc.xpath("//img[@id='sm']").first
        yield true, img_node.attr('src')
      else
        yield false, nil
      end
    end
    @client.start
    @client
  end

  def stop
    @stop = true
    if @client
      @client.cancel
    end
  end

  def reloadPage page, idx, on_complete
    @stop = false
    request_page page.url, false do |success, pic|
      if success
        page.picture = pic
        on_complete.inv true, page
      else
        on_complete.inv false, page
      end
    end
  end
end
