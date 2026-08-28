local class = require("class")

local Example = class(Example)

function Example:test()
    print("Hello from lua!")
end

function Example:init()
    print("Initting from lua")
end

Example._asset_id = 1

register_class("Example", Example)

local example = world:spawn("Example")
example:test()

local id = example._entity_id
local example_from_id = world:getEntityById(id)
example_from_id:test()

print(example._entity_ref.transform.scale_x)