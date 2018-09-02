# React Native Component
This script will create a template for your new components.

I am learning Perl and Shell recently (COMP2041) and wonder if I could write something for practise. 
### How to install
Clone this repo,
```
./install.sh
```
If it does not work, please type
```
chmod 755 install.sh
```
and run it again.

**I think you need to have perl + shell on your machine in order to use this script.**
### How to use
```
rncomponent [filename]
```
This script will create a template for your new component class so that you dont have to type the same thing over and over again. It gives you a basic view with stylesheet and **it won't override existing files.**
### Sample output
```
rncomponent HelloWorld
```
```js
import React, { Component } from 'react';
import { View, Text, StyleSheet } from 'react-native';

class HelloWorld extends Component {
  render() {
    const { container } = styles;
    return (
      <View style={container}>
        <Text>HelloWorld</Text>
      </View>
    )
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center'
  }
})

export { HelloWorld };
```
MIT License
