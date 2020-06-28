fun printMessage(message: String):Unit{
    println(message)
}

fun sum(x:int,y:int){
    return x+y
}

fun multiply(x:int,y:int){
    return x*y
}

fun printMessageWithPrefix(message:String,prefix:String="Info"){
    println("[$prefix] $message")
}
fun main()
{
    printMessage("hello_Kotlin")
    printMessageWithPrefix("Hello","Log")
    printMessageWithPrefix(prefix = "Log",message = "Hello")
    println(sum(1,2))
    println(multiply(4,5))
}