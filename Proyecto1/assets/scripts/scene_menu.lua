scene = {
    -- Tabla de imagenes y sprites
    sprites = {
    },
    -- Tabla de fuentes

    fonts = {
        [0] = {
            fontId = "press_start_24",
            filePath = "assets/fonts/press_start.ttf",
            fontSize = 24
        },
        {
            fontId = "press_start_32",
            filePath = "assets/fonts/press_start.ttf",
            fontSize = 32
        }
    },

    -- Tabla de acciones y teclas
    keys = {
    },

    -- Tabla de acciones y botones del ratón

    buttons = {
        [0] =
        {name = "mouse_left_button", button = 1},

    },
    music = {
        filePath = "assets/music/TestMusic2.wav",
        length = 2000,
    },

    -- Tabla de entidades
    entities = {
        [0] =
        {
            components = {
                text = {
                    text = "Battle of Andronika",
                    fontId = "press_start_32",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 50.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                clickable = {
                }
            },
        },
        {
            components = {
                text = {
                    text = "1 Player",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 100.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                script = {
                    path = "assets/scripts/menu_button_01.lua"
                },
                player = {
                    number = 1
                },
                clickable = {
                }
            }
        },
        {
            components = {
                text = {
                    text = "2 Players",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 150.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                script = {
                    path = "assets/scripts/menu_button_02.lua"
                },
                clickable = {
                }
            }
        }
    }
}
