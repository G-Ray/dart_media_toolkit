import 'package:flutter/material.dart';
import 'dart:async';

import 'package:dart_media_toolkit/dart_media_toolkit.dart'
    as dart_media_toolkit;

  
const mediaPath = 'REPLACE_ME';
const timestamp = 50; // in seconds

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  late int mediaByteOffset;

  @override
  void initState() {
    super.initState();
    mediaByteOffset = dart_media_toolkit.getByteOffset(
        mediaPath,
        timestamp);
  }

  @override
  Widget build(BuildContext context) {
    const textStyle = TextStyle(fontSize: 25);
    const spacerSmall = SizedBox(height: 10);
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Native Packages'),
        ),
        body: SingleChildScrollView(
          child: Container(
            padding: const EdgeInsets.all(10),
            child: Column(
              children: [
                Text(
                  'Byte offset at ${timestamp}s is $mediaByteOffset',
                  style: textStyle,
                  textAlign: TextAlign.center,
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
