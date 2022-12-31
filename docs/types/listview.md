---
title: CutieListView QML Type
---

CutieListView is a component used to display data models in a list format.

Inherits: QtQuick.Controls 2.15 ListView

### Properties

- [menu](#menu): [CutieMenu](menu)

## Detailed Description

Extends QtQuick.Controls 2 ListView with a possibility of an additional hamburger menu overlaid onto the bottom right corner of the view. The menu can be easily enabled and set by using the view's `menu` property and `CutieMenu` QML type.

## Property Documentation

#### menu

[CutieMenu](menu)

Can be set to add a hamburger menu the can be popped up by the user. If not set, the menu button will not be visible.

**Note:** The menu button acts as a footer of the ListView with `footerPositioning` set to `ListView.OverlayFooter`. Setting the `footer` property manually will override this button which makes the menu unusable by the user unless another way of opening tme menu is implemented.