import React, { Component } from 'react';
import { View, Text, StyleSheet } from 'react-native';

export interface MainProps {

}

interface MainState {

}

/**
 * Main Class
 */
class Main extends Component<MainProps, MainState> {
  constructor(props: MainProps) {
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
