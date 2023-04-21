import fs from 'node:fs/promises';

const namespaceTemplate = (content) => `
namespace WebBuiltin {
${content}
}
`

const stringTemplate = (key, value) => `
static const char ${key}[] PROGMEM =
R"==(
${value}
)==";

`
const capitalized = (word) => word.charAt(0).toUpperCase() + word.slice(1)

async function main() {
    let output = ""
    const dir = await fs.readdir('./src')
    
    for (let name of dir) {
        if (name === "assets") {
            continue
        }
        console.log(`Building ${name}`)
        const content = await fs.readFile(`./src/${name}`, { encoding: 'utf8' })
        const splitted = name.split('.')
        const formattedName = splitted[0] + capitalized(splitted [1])
        const c = stringTemplate(formattedName, content)
        output += c
    }

    const toWrite = namespaceTemplate(output)

    const dist = await fs.open('./dist/webbuiltin.hpp', 'w')
    await dist.write(toWrite, 0, 'utf8')
    console.log("Done")
}

main()
