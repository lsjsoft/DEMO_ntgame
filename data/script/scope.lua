module("scope", package.seeall)

----------------------------------------------

local allScope= {}

----------------------------------------------

local scope= {}

function scope:create()
	local obj= {}
	setmetatable(obj, self)
	self.__index = self
	obj.evts= {}
	obj.timer= {}
	return obj
end

function scope:listen(name, func)
	self.evts[name]= self.evts[name] or {}
	self.evts[name][func]= func
	allScope[self]= self
end

function scope:__fire(name, ...)
	local funcs= self.evts[name]
	if funcs== nil then
		return
	end

	for _,fun in pairs(funcs) do
		fun(...)
	end
end

function scope:clear()
	self.evts= {}
	allScope[self]= nil
end

function scope:update(dt)
	for K, v in pairs(self.timer) do
		v.t= v.t+ dt
		if v.t>= v.inv then
			v.t= 0
			v.count= v.count+ 1
			if v.times~= 0 and v.count>= v.times then
				table.remove(self.timer, k)
			end
			v.callback()
		end
	end
end

function scope:setTimer(tm, inv, callback)
	table.insert( self.timer,
		{ times= tm, inv= inv, callback= callback, count=0, t=0 } )

	allScope[self]= self
end

----------------------------------------------

function __update(dt)
	for _, cp in pairs(allScope) do
		cp:update(dt)
	end
end

registerUpdater(__update)

----------------------------------------------

function _G.fireEvent(name, ...)
	for _, v in pairs(allScope) do
		v:__fire(name, ...)
	end
end

function _G.createScope()
	return scope:create()
end

----------------------------------------------

