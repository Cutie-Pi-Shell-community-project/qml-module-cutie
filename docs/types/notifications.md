---
title: CutieNotifications QML Type
---

CutieNotifications provides an interface to interact with a freedesktop.org compliant notification server.

Inherits: QObject

### Methods

- uint [notify](#uint-notifystring-appname-uint-replacesid-string-appicon-string-summary-string-body-list-actions-object-hints-int-expiretimeout)(string appName, uint replacesId, string appIcon, string summary, string body, list<string> actions, object hints, int expireTimeout)

## Detailed Description

CutieNotifications can be used to easily send notifications using the standard D-Bus interface defined by freedesktop.org.

## Method Documentation

#### uint notify(string appName, uint replacesId, string appIcon, string summary, string body, list<string> actions, object hints, int expireTimeout)

Sends a notification with appName, appIcon, summary, and body specified. For more information about the parameters, read [the specification](https://specifications.freedesktop.org/notification-spec/notification-spec-latest.html).

Returns the notification ID returned by the server.
