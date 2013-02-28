
local updateTable= {}

local files=
{
	"../data/script/timer.lua",
	"../data/script/scope.lua",
	"../data/script/test/test_001.lua",
}

function ntError(str)
	print(str)
end

function ntWarning(str)
	print(str)
end

function reload()
	for i, v in ipairs(files) do
		dofile(v)
	end
end

function ntInit()
	gs.print("script init..")
	reload()
	gs.print("script ok..")
end

function ntUpdate(fTime)
	for c, _ in pairs(updateTable) do
		c(fTime)
	end
end

function registerUpdater(callback)
	updateTable[callback]= true
end

