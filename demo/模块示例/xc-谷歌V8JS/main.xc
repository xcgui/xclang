
函数 整型 入口函数()
	文本型   str1 = ""
	"class Car {\n"
	"  constructor(name, year) {\n"
	"    this.name = name;\n"
	"    this.year = year;\n"
	"  }\n"
	"  age() {\n"
	"   let date = new Date(); // This will work\n"
	"   return date.getFullYear() - this.year;\n"
	"  }\n"
	"}"
	调试输出(str1)


	文本型  str2 = ""
	"myCar = new Car(\"Ford\", 2014);\n"
	"myCar.age();"
	
	JSV8引擎类   v8js
	调试输出(v8js.取版本号())

	v8js.初始化()
	调试输出(v8js.执行脚本从字符串(str1))
	调试输出(v8js.执行脚本从字符串(str2))
	v8js.退出()
	
	控制台格式输出("2222\n")
	控制台暂停()
	//延迟(2000)
