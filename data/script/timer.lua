module("timer", package.seeall)

-- user:
-- timer.set(1, 0.1, function() end)

local allTimer={}

function set(times, inv, callback)
	if type(callback)~="function" or type(times)~= "number" or type(inv)~= "number" then
		ntError("timer.set invalid args!")
		return
	end

	table.insert( allTimer,
		{ times= times, inv= inv, callback= callback, count=0, t=0 } )
end

function update(dt)
	for k, v in pairs(allTimer) do
		v.t= v.t+ dt
		if v.t>= v.inv then
			v.t= 0
			v.count= v.count+ 1
			if v.times~= 0 and v.count>= v.times then
				table.remove(allTimer, k)
			end
			v.callback()
		end
	end
end

registerUpdater(update)

