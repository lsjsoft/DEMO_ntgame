
local updateTable= {}

function ntError(str)
	print(str)
end

function ntWarning(str)
	print(str)
end

function ntInit()
	gs.print("script init..")
	dofile("../data/script/timer.lua")
	timer.set(1, 10, function()
		print("ÄãºÃ")
	end)

	timer.set(1, 1, function()
		dofile("../data/script/test/test_001.lua")
	end)
end

function ntUpdate(fTime)
	for c, _ in pairs(updateTable) do
		c(fTime)
	end
end

function registerUpdater(callback)
	updateTable[callback]= true
end

