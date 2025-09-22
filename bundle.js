function Header() {
  const div = document.createElement('div');
  div.innerHTML += `<Header>`;
  div.innerHTML += `    <h1>Tittle h1</h1>`;
  div.innerHTML += `    <h2>Tittle h2</h2>`;
  div.innerHTML += `    <h3>Tittle h3</h3>`;
  div.innerHTML += `    <h4>Tiitle h4</h4>`;
  div.innerHTML += `    <h5>Tiitle h5</h5>`;
  div.innerHTML += `    <h6>Tiitle h6</h6>`;
  div.innerHTML += `</Header>`;
  return div;
}

function App() {
  const div = document.createElement('div');
  div.innerHTML += `<main>`;
  div.innerHTML += `    <h1>Este es el main</h1>`;
  div.innerHTML += `</main>`;
  return div;
}

function Footer() {
  const div = document.createElement('div');
  div.innerHTML += `<footer>`;
  div.innerHTML += `    Hola!`;
  div.innerHTML += `</footer>`;
  return div;
}

