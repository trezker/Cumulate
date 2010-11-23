return {

update = function(dt, entity)
	px, py = player:get_position()
	ex, ey = entity:get_position()
	dx, dy = px-ex, py-ey
	if math.abs(dx) > 3 then
		vx, vy = entity:get_linear_velocity()
		entity:set_fixed_rotation(false)
		entity:set_linear_velocity(dx, vy)
	else
		entity:set_angular_velocity(0)
		entity:set_fixed_rotation(true)
	end
end

}
