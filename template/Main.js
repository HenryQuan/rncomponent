import React, { Component } from 'react';
import { View, Text, StyleSheet } from 'react-native';

/**
 * Main Class
 */
class Main extends Component {
  constructor(props) {
    super(props);
  }

  render() {
    const { container } = styles;
    return (
      <View style={container}>
        <Text>Main</Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1
  }
});

export { Main };
