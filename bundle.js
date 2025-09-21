function Header() {
  const div = document.createElement('div');
  div.innerHTML += `<Header>`;
  div.innerHTML += `    <h2>Este es el header!</h2>`;
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
  div.innerHTML += `    <h3>Footer</h3>`;
  div.innerHTML += `</footer>`;
  return div;
}

