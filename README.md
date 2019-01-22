# rudolph

**Contains the following libraries and executables:**

```
rudolph@0.0.0
│
├─test/
│   name:    TestRudolph.exe
│   main:    TestRudolph
│   require: rudolph.lib
│
├─library/
│   library name: rudolph.lib
│   namespace:    Rudolph
│   require:
│
└─executable/
    name:    RudolphApp.exe
    main:    RudolphApp
    require: rudolph.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x RudolphApp.exe
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
