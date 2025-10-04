
import SwiftUI
import Foundation

@_silgen_name("sch_square")
func sch_square(_ x: Int32) -> Int32

@_silgen_name("sch_add")
func sch_add(_: Int32, _: Int32) -> Int32;

@main
struct SchedulingApp: App {
    init() {
        print("Hello world!")
        
        // Call V
        let result = sch_square(12)
        print(result)
        
        // Call V again
        print(sch_add(10, 11))
    }
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
