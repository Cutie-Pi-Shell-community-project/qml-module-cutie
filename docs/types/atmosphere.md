---
title: Atmosphere QML Type
---

Atmosphere holds information about currently used Atmosphere (theme) in Cutie.

Inherits: QObject

### Properties

- [path](#path): string
- [variant](#variant): string

## Detailed Description

This singleton type is used to retrieve information about the currently used Atmosphere (theme). This makes it possible to theme custom components consistently.

## Property Documentation

#### path

string, readonly

Holds the path to the atmosphere directory which contains the atmosphere metadata and the wallpaper.

#### variant

string, readonly

Holds "dark" or "light" depending on the atmosphere. Dark atmospheres usually have darker wallpaper and use light foreground colors, whereas light atmospheres have lighter wallpaper and use dark foreground colors.