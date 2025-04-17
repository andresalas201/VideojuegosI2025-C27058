var_nombre = "Andre Salas"
var_edad = 20

table_config = {
    title = "Tarea 01 con LUA",
    fullscreen = true;
    resolution = {
        width = 800,
        height = 600
    },
}

function factorial(n)
    if n == 1 then
        return 1
    end
    return n * factorial(n-1)
end

print("[LUA] var_nombre: "..var_nombre)
print("[LUA] var_edad: "..var_edad)

var_pow = pow(2,4)
print("[LUA] 2**4: "..var_pow)