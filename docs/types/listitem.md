---
title: ListItem QML Type
---

ListItem is a selectable list item styled to fit Cutie UI visual language.

Inherits: QtQuick.Controls 2.15 Button

### Properties

- [subText](#subtext): string
- [iconOverlay](#iconoverlay): bool
- [menu](#menu): [CutieMenu](menu)

## Detailed Description

Extends QtQuick.Controls 2 Button to function as a selectable item in [ListViews](listview) and to fit Cutie UI. It supports adding context menus easily by using its `menu` property and `CutieMenu` QML type.

## Property Documentation

#### subText

string

An optional text shown below the actual text in `text` property. By default, this is shown using a smaller font size that the main text.

#### iconOverlay

bool

If true, filters the icon to be colored black or white depending on the atmosphere variant. By default, this is set to true.

#### menu

[CutieMenu](menu)

Can be set to add a context menu the will pop up on `pressAndHold` signal.