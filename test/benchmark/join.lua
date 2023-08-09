local start = os.clock()
local list = {}
for i = 0, 9999 do
  list[i] = i
end

local sum = table.concat(list,'\n')
io.write("0\n")
io.write(string.format("elapsed: %.8f\n", os.clock() - start))