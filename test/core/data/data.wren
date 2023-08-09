var a=Data.new(100)
a.add("foo")
a.add("bar")

System.print(a) // expect: foobar
System.print(a.length) // expect: 6
System.print(a.capacity) // expect: 100