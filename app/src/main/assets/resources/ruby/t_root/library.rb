require 'object'
require 'models'
require 'http_client'
require 'callback'
require 'data'
require 'xml'

class Library < HiEngine::Object

  def host_url is_ex
    if is_ex then 'https://exhentai.org' else 'https://e-hentai.org' end
  end

  def parse path, igneous, on_complete
    begin
      doc = XMLDocument.new FileData.new(path), 1
      books = []
      nodes = doc.xpath "//table[@class='itg']//tr[@class='gtr0' or @class='gtr1']"
      nodes.each do |node|
        img_node = node.xpath("td//div[@class='it2']").first
        book = Book.new
        imgs = img_node.xpath('img')
        if imgs.size == 0
          str = img_node.getContent
          str.gsub!('inits~', 'https://')
          arr = str.split '~'
          if arr.size >= 2
            book.thumb = arr[0..1].join '/'
          end
        else
          img = imgs[0]
          book.thumb = img.attr 'src'
        end
        is_ex = settings.find 'Switch'
        if is_ex and igneous != nil
          get_passid do |p_id, p_secret|
            book.thumb_headers = {'Cookie' => "igneous=#{igneous};"}
          end
        end

        title_node = node.xpath("td//div[@class='it5']/a").first
        book.url = title_node.attr 'href'
        book.name = title_node.getContent.strip
        book.subtitle = node.xpath("td[@class='itd']").first.getContent.strip
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

  def get_passid 
    p_id = settings.find 'pass_id'
    p_secret = settings.find 'pass_secret'
    yield p_id, p_secret
  end

  # @description 加载主页接口。
  # @param page 分页，从0开始
  # @param on_complete 结束回调
  # @return client 把请求反回，让主程序页面退出的时候有能力结束请求。
  #   不过这个client并不是关键要素，所以有一串请求时也不必担心，返回最开始的一个就行。
  def load page, on_complete
    is_ex = settings.find 'Switch'
    url = "#{host_url is_ex}/?#{append}&page=#{page}&f_apply=Apply+Filter"
    if is_ex
      get_passid do |p_id, p_secret| 
        client = HTTPClient.new url
        client.addHeader 'Cookie', "ipb_member_id=#{p_id}; ipb_pass_hash=#{p_secret}"
        client.on_complete = Callback.new do |c|
          if c.getError.length == 0
            set_cookie = c.response_headers['Set-Cookie']
            igneous = set_cookie[/(?<=igneous\=)[^;]+/]
            parse c.path, igneous, on_complete
          else
            on_complete.invoke [false]
          end
        end
        client.start
        client
      end
    else
      client = HTTPClient.new url
      client.on_complete = Callback.new do |c|
        if c.getError.length == 0
          parse c.path, nil, on_complete
        else
          on_complete.invoke [false]
        end
      end
      client.start
      client
    end

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

    is_ex = settings.find 'Switch'
    url = "#{host_url is_ex}/?page=#{page}&f_search=#{HTTP::URL::encode key}&f_sname=1&#{append}&f_stags=1&f_apply=Apply+Filter"
    if is_ex
      get_passid do |p_id, p_secret| 
        client = HTTPClient.new url
        client.addHeader 'Cookie', "ipb_member_id=#{p_id}; ipb_pass_hash=#{p_secret}"
        client.on_complete = Callback.new do |c|
          if c.getError.length == 0
            set_cookie = c.response_headers['Set-Cookie']
            igneous = set_cookie[/(?<=igneous\=)[^;]+/]
            parse c.path, igneous, on_complete
          else
            on_complete.invoke [false]
          end
        end
        client.start
        client
      end
    else
      client = HTTPClient.new url
      client.on_complete = Callback.new do |c|
        if c.getError.length == 0
          parse c.path, nil, on_complete
        else
          on_complete.invoke [false]
        end
      end
      client.start
      client
    end

  end

end
