local function class(base)
    local cls = {}

    cls.__index = cls
    cls.super = base

    setmetatable(cls, {
        __index = base
    })

    function cls:new(...)
        local instance = setmetatable({}, cls)

        if instance.init then
            instance:init(...)
        end

        return instance
    end

    return cls
end

return class