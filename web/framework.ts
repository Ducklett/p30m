/*
A basic typescript framework that works by extending html elements
instead of wrapping or replacing them by virtual components
the primitive syntax is jquery-esque with a fluid $this().$that() API
high level components are added on top to make things more
reusable, composable and easy to work with

inspired by:
- my previous "dom fluid" api               https://github.com/Ducklett/wewrss/blob/master/src/domfluid.ts
- grecha.js                                 https://github.com/tsoding/grecha.js
- flutter                                   https://flutter.dev/
*/
interface HTMLElement {
    $click: (f: () => any) => HTMLElement
    $child: (c: HTMLElement) => HTMLElement
    $children: (...cs: HTMLElement[]) => HTMLElement
    $class: (c: string) => HTMLElement
    $text: (t: string) => HTMLElement
}

const body = document.body;

HTMLElement.prototype.$click = function (f) {
    this.addEventListener('click', f);
    return this;
}
HTMLElement.prototype.$child = function (c) {
    this.appendChild(c)
    return this;
}
HTMLElement.prototype.$children = function (...cs) {
    cs.forEach(c => {
        this.appendChild(c)
    });
    return this;
}
HTMLElement.prototype.$class = function (c) {
    this.classList.add(c)
    return this;
}
HTMLElement.prototype.$text = function (t) {
    this.textContent = t
    return this;
}

const $ = (name: string) => document.createElement(name);

const lorem = `Lorem ipsum dolor sit, amet consectetur adipisicing elit. Recusandae, debitis aperiam! Illo id dicta esse fugiat explicabo maiores beatae quibusdam atque ex molestiae suscipit provident voluptas, dolor eius ipsum quasi?`;


type Router = {
    changePage: (n: number) => void
} & HTMLElement

function router(...pages: HTMLElement[]): Router {
    const html: any = $('div').$class('router').$child(pages[0])
    Object.assign(html, router.prototype);
    html.pages = pages;
    return html;
}

router.prototype.changePage = function (n: number) {
    this.innerHTML = '';
    this.appendChild(this.pages[n])
}

const button = (text: string, onClick: () => any) => $('button')
    .$text(text)
    .$click(onClick)

const header = (...children: HTMLElement[]) => $('header').$children(...children)
const content = (...children: HTMLElement[]) => $('div').$class('content').$children(...children)
const footer = (...children: HTMLElement[]) => $('footer').$children(...children)
const text = (text: string) => $('p').$text(text)
const createApp = (parent: HTMLElement, content: HTMLElement) => parent.$child(content)
// =====================================

let myRouter: Router;

const toPage = (n: number) => () => myRouter.changePage(n)

createApp(body, content(
    header(
        button('Page 1', toPage(0)),
        button('Page 2', toPage(1)),
    ),
    myRouter = router(
        $('div').$children(
            $('h2').$text('page 1'),
            text(lorem)
        ),
        $('div').$children(
            $('h2').$text('page 2'),
            text(lorem)
        ),
    ),
    footer(text('copyright 2021 gigacorp, this took us years to engineer!'))
),
);
