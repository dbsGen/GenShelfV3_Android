require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'xml'

class Library < HiEngine::Object

  HOST_URL = 'https://e-hentai.org/lofi'

  def parse path, on_complete
    begin
      doc = XMLDocument.new FileData.new(path), 1
      books = []
      nodes = doc.xpath "//div[@id='ig']/div[@class='ig']"
      nodes.each do |node|
        img = node.xpath("table/tr/td[@class='ii']/a/img").first
        book = Book.new
        book.thumb = img.getAttribute 'src'
        rows = node.xpath "table/tr/td/table[@class='it']/tr"
        title_node = rows[0].xpath('td/a').first
        book.url = title_node.getAttribute 'href'
        book.name = title_node.getContent.strip
        book.subtitle = rows[1].xpath('td[@class="ip"]').first.getContent.strip
        book.des = rows[3].xpath('td[2]').first.getContent.strip
        books << book
      end
      on_complete.invoke [true, books]
    rescue Exception => e
      p e
      on_complete.invoke [false]
    end
  end

  def append
    str = "f_doujinshi=#{settings.find('DOUJINSHI')}&"
    str << "f_manga=#{settings.find('MANGA')}&"
    str << "f_artistcg=#{settings.find('ARTIST GS')}&"
    str << "f_gamecg=#{settings.find('GAME CG')}&"
    str << "f_western=#{settings.find('WESTERN')}&"
    str << "f_non-h=#{settings.find('NON-H')}&"
    str << "f_imageset=#{settings.find('IMAGE SET')}&"
    str << "f_cosplay=#{settings.find('COSPLAY')}&"
    str << "f_asianporn=#{settings.find('ASIAN PORN')}&"
    str << "f_misc=#{settings.find('MISC')}"
  end

  # @description 加载主页接口。
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  #   不过这个client并不是关键要素，所以有一串请求时也不必担心，返回最开始的一个就行。
  def load page, on_complete
    append
    url = "#{HOST_URL}/?#{append}&page=#{page}&f_apply=Apply+Filter"

    client = HTTPClient.new url
    client.on_complete = Callback.new do |c|
      if c.getError.length == 0
        parse c.path, on_complete
      else
        on_complete.invoke [false]
      end
    end
    client.start
    client
  end

  # @description 读去书本详细信息的接口。
  # @param book Book对象
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  def loadBook book, page, on_complete
    chapter = Chapter.new
    chapter.name = 'Chapter 1'
    chapter.url = book.url
    on_complete.invoke [true, book, [chapter], false]
    nil
  end

  # @description 搜索接口
  # @param key 搜索关键字
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  def search key, page, on_complete
    url = "#{HOST_URL}/?page=#{page}&f_search=#{HTTP::URL::encode key}&f_sname=1&#{append}&f_stags=1&f_apply=Apply+Filter"
    client = HTTPClient.new url
    client.on_complete = Callback.new do |c|
      if c.getError.length == 0
        parse c.path, on_complete
      else
        on_complete.inv false
      end
    end
    client.start
    client
  end

end
