function check_end(max_score, current_score)

    if (max_score <= current_score) then
        spawn_boss(this)
    end

end