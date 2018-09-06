require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'gumbo'
require 'encoder'

class Library < HiEngine::Object

  HOST_URL = 'http://m.baobaoman.com'

  def parse path
    utf8d = Encoder.decode FileData.new(path), 'gb2312'
    doc = GBDocument.new utf8d
    books = []
    nodes = doc.css "ul.pic.pic1 > li"
    nodes.each do |node|
      book = Book.new
      book.thumb = node.css('img').first.attr('src')
      title_node = node.css('.txt').first
      book.url = HOST_URL + title_node.attr('href')
      book.subtitle = book.name = title_node.getContent
      
      books << book
    end

    ps = doc.css('.showpage > li')
    no_more = true
    ps.each do |p|
      if p.getContent == '下一页'
        no_more = false
        break
      end
    end
    yield true, books, no_more
  end

  def host_url page
    unless @types
      @types = JSON.parse(file('types.json').text).values 
    end
    t = settings.find('类别') || 0
    st = @types[t]
    "#{HOST_URL}/#{st['t']}/list_#{st['n']}_#{page+1}.html"
  end

  # 加载主页接口。
  # @method load
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # => 成功: on_complete.inv true, books([Book...]), no_more(bool)
  # => 失败: on_complete.inv false
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  #   不过这个client并不是关键要素，所以有一串请求时也不必担心，返回最开始的一个就行。
  def load page, on_complete
    url = host_url(page)

    client = HTTPClient.new url
    client.on_complete = Callback.new do |c|
      if c.getError.length == 0
      	parse c.path do |success, books, no_more|
        	on_complete.inv success, books, no_more
      	end
      else
        on_complete.invoke [false]
      end
    end
    client.start
    client
  end

  # 读去书本详细信息的接口。
  # @method loadBook
  # @param book Book对象
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # => 成功: on_complete.inv true, new_book(Book), chapters([Chapter...]), no_more(bool)
  # => 失败: on_complete.inv false
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  def loadBook book, page, on_complete
    chapter = Chapter.new 
    chapter.url = book.url
    chapter.name = "Chapter"

    on_complete.inv true , book, [chapter], false
  end

  # @description 搜索接口
  # @param key 搜索关键字
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # => 成功: on_complete.inv true, books([Book...]), no_more(bool)
  # => 失败: on_complete.inv false
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  def search key, page, on_complete
    url = "http://m.baobaoman.com/plus/search.php?kwtype=0&q=#{Encoder.urlEncodeWithEncoding key, 'gb2312'}"
    
    client = HTTPClient.new url
    client.on_complete = Callback.new do |c|
      if c.getError.length == 0
      	parse c.path do |success, books, no_more|
        	on_complete.inv success, books, no_more
      	end
      else
        on_complete.invoke [false]
      end
    end
    client.start
    client 
  end

end
