require 'models'

class Settings < HiEngine::Object
  
  def process
    begin
      item = SettingItem.new
      item.name = 'DOUJINSHI'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'MANGA'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'ARTIST GS'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'GAME CG'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'WESTERN'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'NON-H'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'IMAGE SET'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'COSPLAY'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'ASIAN PORN'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'MISC'
      item.type = 3
      item.default_value = true
      addItem item

      item = SettingItem.new
      item.name = 'ExHentai'
      item.type = 6
      addItem item

      item = SettingItem.new
      item.name = 'Switch'
      item.type = 4
      item.default_value = false
      addItem item

      @login_item = SettingItem.new
      @login_item.name = 'Login'
      @login_item.type = 7
      @web_view_listener = Callback.new do |cookies|
        begin
          p_id = cookies[/(?<=ipb_member_id\=)[^;]+/]
          p_secret = cookies[/(?<=ipb_pass_hash\=)[^;]+/]
          if p_id and p_secret
            set 'pass_id', p_id
            set 'pass_secret', p_secret
            message 'OK!'
          else
            message 'No token!'
          end

        rescue Exception => e
          message "No cookies!"
        end
      end
      @login_item.params = Callback.new do
        openWebView('https://forums.e-hentai.org/index.php?act=Login&CODE=00', 'Login E-Hentai', @web_view_listener)
      end
      addItem @login_item
    rescue Exception => e
      p e

    end
  end
end
