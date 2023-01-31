---
title: CutieOfonoModem QML Type
---

CutieOfonoModem provides an interface to interact with a modem exported on the Ofono D-Bus service.

Inherits: CutieModem

### Properties

- [data](#data): object
- [path](#path): string
- [simData](#simdata): object

### Methods

- void [sendMessage](#void-sendmessagestring-to-string-message)(string to, string message)

## Detailed Description

The list of modems returned by [CutieModemSettings](modemsettings) contains objects inheriting an abstract type CutieModem. For modems managed by Ofono, the type CutieOfonoModem will be used to provide access to the modem. Currently, only Ofono is supported.

## Property Documentation

#### data

object, readonly

Holds a JavaScript object containing the modem properties as given by [Ofono](https://git.kernel.org/pub/scm/network/ofono/ofono.git) D-Bus service.

#### path

string, readonly

Holds the D-Bus path that is used by [Ofono](https://git.kernel.org/pub/scm/network/ofono/ofono.git) to describe this modem.

#### simData

object, readonly

Holds a JavaScript object containing the properties of the SIM card inserted into the modem as given by [Ofono](https://git.kernel.org/pub/scm/network/ofono/ofono.git) D-Bus service.

## Method Documentation

#### void sendMessage(string to, string message)

Sends a SMS message using a modem represented by this object. The SMS will be sent to the recepient passed in the argument `to` and the SMS will have a message body as passed in the argument `message`.