-- Variables globales
player_velocity = 150;
fixed_player_velocity = math.sqrt((player_velocity*player_velocity) / 2);


function update()
    set_velocity(this, 0, 0)
    vel_x = 0;
    vel_y = 0;
    if is_action_activated("up2") then
        vel_y = vel_y + -1
    end
    if is_action_activated("left2") then
        vel_x = vel_x + -1
    end
    if is_action_activated("right2") then
        vel_x = vel_x + 1
    end
    if is_action_activated("down2") then
        vel_y = vel_y + 1
    end
    if is_action_activated("shoot2") then
        shoot(this)
    end
 
    if vel_x ~= 0 and vel_y ~= 0 then
        vel_x = vel_x * fixed_player_velocity
        vel_y = vel_y * fixed_player_velocity
    else
        vel_x = vel_x * player_velocity
        vel_y = vel_y * player_velocity
    end
    set_velocity(this, vel_x, vel_y)
    set_sprite(this)
end