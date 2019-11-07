import json

x = {
  "name": "John",
  "age": 30,
  "married": True,
  "divorced": False,
  "children": ("Ann","Billy"),
  "pets": None,
  "cars": [
    {"model": "BMW 230", "mpg": 27.5},
    {"model": "Ford Edge", "mpg": 24.1}
  ]
}
with open("output.json" , "w") as outfile :
    json.dump(x , outfile)

  
with open("output.json" , "r") as outfile :
    y = json.load(outfile)

print(y)