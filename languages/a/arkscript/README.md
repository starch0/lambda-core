# ArkScript

Running this solution requires either ArkScript 4.0.0 or a pre-release of ArkScript 4.0.0.

## Running the solution (docker)

```
docker pull arkscript/nightly:latest
docker run -it --rm -v $(pwd):/tmp:ro arkscript/nightly /tmp/lambda-core.ark
```

## Running the solution (binary)

Download the binary for your platform in [the latest 4.0.0 pre-release](https://github.com/ArkScript-lang/Ark/releases/tag/v4.0.0-10).

Extract the zip, you will need both `arkscript` and `libArkReactor.(so|dll)` in the same directory.

```
chmod u+x arkscript
./arkscript lambda-core.ark
```

## Other way of installing ArkScript

See the documentation: [arkscript-lang.dev/tutorials/building.html](https://arkscript-lang.dev/tutorials/building.html).

