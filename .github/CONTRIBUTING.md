# Contribution guidelines

First off, thank you for your interest in contributing to this project! Below are some guidelines and conventions for the project.

## Code

For readability and consistency, please follow the same code conventions when modifying the code base.
- Indent blocks with size 4 tabs
- Braces opening blocks (except for `case` blocks) should appear on the same line as the block opening
- For conditionals and loops, include a space between the close paren and the opening brace
- If braces are required in a `case` block to define a scope in which new variables can be declared, the opening brace should come on the line following the `case` statement. The final `break` for that block should be outside the braces.
- Constants and enum values should be in all caps
- Variables should be in camel casing
- Include spacing before and after operators

## Sprite maps

Sprite maps in Dork 2 contain four animations: one for walking in each direction. The frames for each animation should be placed in a single row with no whitespace between them. Each frame must have the same dimensions. If the entity does not occupy the entire frame (e.g. for the side views) please center the entity in the frame. Existing animations are all three frames, but the frame count isn't set in stone.

The frame size is not the same for each entity. If it makes sense for a mob to be bigger or smaller, then its texture should reflect this.

By convention, the sprite map should be in PNG format and named `XSpriteMap.png` where `X` is the name of the entity and stored in the `Sprites` folder.

## Attribution/Legal

All assets in Dork 2 are and must be available under open licenses such as Creative Commons.

If you create any assets, please modify the `CREDITS` file to include your contribution.

If you contribute to the code base, please include a copyright notice at the top of each file you modify. This should have the form
```
Copyright (C) YEAR NAME
```
