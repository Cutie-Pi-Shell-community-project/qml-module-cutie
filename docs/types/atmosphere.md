---
title: Atmosphere QML Type
---

Atmosphere holds information about currently used Atmosphere (theme) in Cutie.

Inherits: QObject

### Properties

- [path](#path): string
- [variant](#variant): string

## Detailed Description

This singleton type is used to retireve information about the currently used Atmosphere (theme). This allows styling custom components appropriately.

## Property Documentation

#### path

string, readonly

Holds the path to the atmosphere directory which contains the atmosphere metadata and the wallpaper.

#### variant

string, readonly

Holds "dark" or "light" depending on the atmosphere. Dark atmospheres usually have darker wallpaper and use light foreground colors, whereas light atmospheres have lighter wallpaper and use dark foreground colors.