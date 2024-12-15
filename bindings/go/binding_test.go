package tree_sitter_alcha_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_alcha "github.com/jpt13653903/tree-sitter-alcha/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_alcha.Language())
	if language == nil {
		t.Errorf("Error loading Alcha grammar")
	}
}
