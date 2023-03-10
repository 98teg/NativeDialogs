# `NativeNotification`

## Description

This node would show the user a brief message and then fade away.

![Native Notification](./images/native_notification.png)

## Properties

|Type|Name|Default value|
|-|-|-|
|[`Icon`](#enum-icon)|[`notification_icon`](#icon-notification_icon--1)|`1`|
|`String`|[`notification_text`](#string-notification_text--)|`""`|
|`String`|[`title`](#string-title--alert)|`"Alert!"`|

## Methods

|Returned type|Declaration|
|-|-|
|`void`|[`send()`](#void-send)|

## Enumerations

### `enum Icon`

```gdscript
Icon ICON_INFO = 0
```

Usually an icon with the letter i in a blue circle*.

```gdscript
Icon ICON_WARNING = 1
```

Usually an icon with an exclamation mark in a yellow triangle*.

```gdscript
Icon ICON_ERROR = 2
```

Usually an icon with a cross in a red circle*.

**(*)** Depends on your OS theme.

## Property Descriptions

### `Icon notification_icon = 1`

The icon displayed by the notification.

```gdscript
void set_icon(Icon value)

Icon get_icon()
```

### `String notification_text = ""`

The text displayed by the notification.

```gdscript
void set_text(String value)

String get_text()
```

### `String title = "Alert!"`

The notification's title.

```gdscript
void set_title(String value)

String get_title()
```

## Method Descriptions

### `void send()`

Sends the notification to appear to the user and then fade away.
