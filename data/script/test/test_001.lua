local plugName= "mySimple"
local plugType= "nifSimple"
local scope= createScope()

function a()
	gs.addPlug(plugType, plugName)
end

function b()
	gs.addNif(plugName, "../data/effect/BUFF_FX042.nif")
end

function c()
	scope:listen("11", function(...) gs.print("myEvent01 call!") end)
	scope:setTimer(1, 1, function() gs.print("haha") end)
end

function d()
	fireEvent("11")
end
