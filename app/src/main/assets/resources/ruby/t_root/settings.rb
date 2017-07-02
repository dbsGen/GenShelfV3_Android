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
    rescue Exception => e
      p e

    end
  end
end
