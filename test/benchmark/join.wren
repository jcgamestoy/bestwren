var p=[]

var start = System.clock
for(i in 0...10000) {
  p.add(i)
}

var r=p.join("\n")

System.print("0")
System.print("elapsed: %(System.clock - start)")

