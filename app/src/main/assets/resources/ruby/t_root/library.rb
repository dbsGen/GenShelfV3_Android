require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'xml'

class Library < HiEngine::Object

  HOST_URL = 'http://manhua.fzdm.com/'

  @books = []

  def parse path, on_complete
    begin
      doc = XMLDocument.new FileData.new(path), 1
      items = doc.xpath "//*[@id='mhmain']//*[@class='round']"
      books = []
      items.each do |item|
        book = Book.new
        book.url = HOST_URL + item.xpath('li//a').first.getAttribute('href')
        book.thumb = 'http:' + item.xpath('li//img').first.getAttribute('src')

        book.name = item.getContent.strip
        books << book
      end
      @books = books
      on_complete.invoke [true, books]
    rescue Exception => e
      on_complete.invoke [false]
    end
  end

  def parse_book ori, path, on_complete
    begin
      doc = XMLDocument.new FileData.new(path), 1

      chapters = []
      items = doc.xpath "//li[contains(@class, 'pure-u-1-2')]/a"
      items.each do |item|
        chapter = Chapter.new
        chapter.url = ori.url + item.getAttribute('href')
        chapter.name = item.getContent.gsub ori.name, ''
        chapters << chapter
      end

      on_complete.invoke [true, ori, chapters, false]
    rescue Exception => e
      p e
      on_complete.inv false
    end
  end

  # @description 加载主页接口。
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  #   不过这个client并不是关键要素，所以有一串请求时也不必担心，返回最开始的一个就行。
  def load page, on_complete
    if page == 0
      client = HTTPClient.new HOST_URL
      client.on_complete = Callback.new do |c|
        if c.getError.length == 0
          parse c.path, on_complete
        else
          on_complete.invoke [false]
        end
      end
      client.start
      client
    else
      on_complete.inv true, []
    end
  end

  # @description 读去书本详细信息的接口。
  # @param book Book对象
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  def loadBook book, page, on_complete
    if page == 0
      client = HTTPClient.new book.url
      client.on_complete = Callback.new do |c|
        if c.getError.length == 0
          parse_book book, c.path, on_complete
        else
          on_complete.invoke [false]
        end
      end
      client.start
      client
    else
      on_complete.inv true, book, [], false
    end
  end

  # @description 搜索接口
  # @param key 搜索关键字
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  def search key, page, on_complete
    begin
      if page == 0
        books = []
        @books.each do |book|
          books << book if book.name[key] != nil
        end
        on_complete.inv true, books
      else

        on_complete.inv true, []
      end
    rescue Exception => e
      on_complete.inv false
    end
  end

end
