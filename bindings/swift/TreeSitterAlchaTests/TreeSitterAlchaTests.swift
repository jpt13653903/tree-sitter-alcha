import XCTest
import SwiftTreeSitter
import TreeSitterAlcha

final class TreeSitterAlchaTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_alcha())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Alcha grammar")
    }
}
