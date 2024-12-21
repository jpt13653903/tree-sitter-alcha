// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterAlcha",
    products: [
        .library(name: "TreeSitterAlcha", targets: ["TreeSitterAlcha"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterAlcha",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                "src/scanner.c",
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterAlchaTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterAlcha",
            ],
            path: "bindings/swift/TreeSitterAlchaTests"
        )
    ],
    cLanguageStandard: .c11
)
