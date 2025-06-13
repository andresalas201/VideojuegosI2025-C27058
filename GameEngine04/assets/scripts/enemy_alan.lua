function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    print(this_tag.." colisiona con "..other_tag)
end