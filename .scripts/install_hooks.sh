#!/bin/bash
set -e  # Exit immediately if any command exits with a non-zero status

# Get the root of the git repository
ROOT_DIR=$(git rev-parse --show-toplevel)
HOOKS_DIR="$ROOT_DIR/.git/hooks"
SCRIPTS_DIR="$ROOT_DIR/.scripts"

# Copy pre-commit hook
echo "Installing pre-commit hook..."
cp "$SCRIPTS_DIR/pre-commit" "$HOOKS_DIR/pre-commit"
chmod +x "$HOOKS_DIR/pre-commit"

# Copy pre-push hook
echo "Installing pre-push hook..."
cp "$SCRIPTS_DIR/pre-push" "$HOOKS_DIR/pre-push"
chmod +x "$HOOKS_DIR/pre-push"

echo "Hooks installed successfully."
