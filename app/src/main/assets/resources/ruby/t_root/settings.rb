require 'models'

class Settings < HiEngine::Object
  def process
    begin

      p "Setting begin!"
      item = SettingItem.new
      item.name = '类别'
      item.type = 1
      item.params = JSON.parse(file('types.json').text).keys
      addItem item

    rescue Exception => e
      p e
    end
  end
end
