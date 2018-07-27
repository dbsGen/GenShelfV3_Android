require 'models'

class Settings < HiEngine::Object
  def process
    begin
      item = SettingItem.new
      item.name = 'ceshi1'
      item.type = 2
      item.default_value = "nihao"

      addItem item
    rescue Exception => e
      p e

    end
  end
end
