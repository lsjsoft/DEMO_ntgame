local plugName= "mySimple"
local plugType= "nifSimple"

function a()
	gs.addPlug(plugType, plugName)
end

function b()
	gs.addNif(plugName, "../data/effect/BUFF_FX042.nif")
end

function c()
	local scope= createScope()
	scope:listen("11", function(...) gs.print("myEvent01 call!") end)
end

function d()
	fireEvent("11")
end
