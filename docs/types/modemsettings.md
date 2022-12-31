---
title: CutieModemSettings QML Type
---

CutieModemSettings provides an interface to access the modems.

Inherits: QObject

### Properties

- [modems](#modems): list&lt;CutieModem&gt;

## Detailed Description

CutieModemSettings is a singleton type providing settings and system integration interface for applications that need access to the modem. Currently, it supports modems found on [Ofono](https://git.kernel.org/pub/scm/network/ofono/ofono.git) D-Bus service, but support for [ModemManager](https://www.freedesktop.org/wiki/Software/ModemManager/) is planned.

## Property Documentation

#### modems

list&lt;CutieModem&gt;, readonly

Holds a list of the available modems. See [CutieOfonoModem](ofonomodem) for information about interacting with the listed modems.