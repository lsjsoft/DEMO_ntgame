module("scope", package.seeall)

local scope= {}
local allScope= {}

function scope:create()
	local obj= {}
	setmetatable(obj, self)
	self.__index = self
	obj.evts= {}
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

function _G.fireEvent(name, ...)
	for _, v in pairs(allScope) do
		v:__fire(name, ...)
	end
end

function _G.createScope()
	return scope:create()
end
