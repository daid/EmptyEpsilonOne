--- @name: Test
--  @author: Daid
--  @minimal version: 1
--  @category: Experimental
--  @description: Description of the scenario
--   		      with multiline support.
--  @variation: Normal
--  @variation: Quick
--              Faster version of the scenario.

function init()
	for x=-1000,1000,100 do
		for y=-1000,1000,100 do
			a = Asteroid({x, y})
		end
	end
	PlayerCraft({50, 50})
	PlayerCraft({2050, 50})
end
