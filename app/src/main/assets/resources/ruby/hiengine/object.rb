module HiEngine
  class Object
    def initialize
      native_initialize
    end

    def native_initialize
    end
    
    def method_missing name, *arg
      native_call name, arg
    end
    
    def self.method_missing name, *arg
      native_class_call name, arg
    end
  end
end
