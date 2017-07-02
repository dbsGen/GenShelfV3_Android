require 'object'

class XMLDocument < HiEngine::Object
    native "hirender::XMLDocument"
    
end
class XMLNode < HiEngine::Object
    native "hirender::XMLNode"

    def attr key
        getAttribute key
    end
end
